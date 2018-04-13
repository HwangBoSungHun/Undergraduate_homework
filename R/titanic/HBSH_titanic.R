rm(list=ls())
library(dplyr)
library(caret)
library(DMwR)
library(ROCR)
library(randomForest)

setwd("~/Desktop/titanic")
train <- read.csv("train.csv")
test <- read.csv("test.csv")
## Preprocessing Data
train1 <- train[, c(1, 2, 3, 5, 6, 7, 8, 10, 12)]
train_Survived <- train[, "Survived"]
train2 <- knnImputation(train1) # Handling NA using knn Imputation 
train2.cat <- train2[, c(3, 4, 9)] # Categorical var
train2.num <- train2[, -c(1, 2, 3, 4, 9)] # Numerical var
train2.cat.dummy <- model.matrix(~factor(Pclass) + Sex + Embarked, data = train2.cat)
train2.cat2 <- train2.cat.dummy[, 2:ncol(train2.cat.dummy)]
train2.num.scaled <- scale(train2.num)
train2.num.pr <- prcomp(train2.num.scaled) # Principal Components of Numeric var
summary(train2.num.pr) # Result of PCA inform that all variables are important

train3 <- cbind(train_Survived, train2.cat2, train2.num.scaled)

test1 <- test[, c(1, 2, 4, 5, 6, 7, 9, 11)]
test2 <- knnImputation(test1) # Handling NA using knn Imputation 
test2.cat <- test2[, c(2, 3, 8)]
test2.num <- test2[, c(4, 5, 6, 7)]
test2.cat.dummy <- model.matrix(~factor(Pclass) + Sex + Embarked, data = test2.cat)
test2.cat2 <- test2.cat.dummy[, 2:ncol(test2.cat.dummy)]
test2.num.scaled <- scale(test2.num)

test3 <- cbind(test2.cat2, test2.num.scaled)

## Partioning Data

# (1) train data (600) - validation data (291) - test data (418)
trainData <- as.data.frame(train3[1:600,])  
validationData <- as.data.frame(train3[601:nrow(train3),])
testData <- as.data.frame(test3)
# (2) k - fold Cross Validation (k = 5)

# (3) Bagging(Bootstrape aggregating)


## Selecting Model

###################################################
# (1) Logistic Regression
model.glm1 <- glm(train_Survived ~ ., family = "binomial", trainData)
model.glm2 <- glm(train_Survived ~ `factor(Pclass)2` +
                    `factor(Pclass)3` + Sexmale + Age + SibSp, family = "binomial", trainData)
summary(model.glm1)
model.pre1 <- predict(model.glm1, newdata = validationData, type = "response")
pr1 <- prediction(model.pre1, validationData$train_Survived)
prf1 <- performance(pr1, measure = "tpr", x.measure = "fpr")
plot(prf1)

summary(model.glm2)
model.pre2 <- predict(model.glm2, newdata = validationData, type = "response")
pr2 <- prediction(model.pre2, validationData$train_Survived)
prf2 <- performance(pr2, measure = "tpr", x.measure = "fpr")
plot(prf2)
performance(pr2, measure = "auc")
predictedResult <- list()
for(i in 1:9){
  predictedResult[[i]] <- ifelse(model.pre1 > i*0.1, 1, 0)
  print(i)
  print(confusionMatrix(predictedResult[[i]], validationData$train_Survived))
}

model.pre3 <- predict(model.glm1, newdata = testData, type = "response")
Result1 <- ifelse(model.pre3 > 0.6, 1, 0)
Result2 <- cbind(test$PassengerId, Result1)
colnames(Result2) <- c("PassengerId", "Survived")
write.csv(Result2, file = "gender_submission.csv", row.names = TRUE)


###################################################
# (2) Decision Tree

# (3) Random Forest
trainRF <- train2[1:700, 2:9]
validateRF <- train2[701:nrow(train2), 2:9]
testRF <- test2[, 2:8]

model_RF <- randomForest(Survived ~ Pclass + Sex + Age + Fare + Embarked, data = trainRF)
pred_RF <- predict(model_RF, validateRF)

predictedResult2 <- list()
for(i in 1:9){
  predictedResult2[[i]] <- ifelse(pred_RF > i*0.1, 1, 0)
  print(i)
  print(confusionMatrix(predictedResult2[[i]], validateRF$Survived))
}
modelRF.pre <- predict(model_RF, newdata = testRF, type = "response")
ResultRF <- ifelse(modelRF.pre > 0.6, 1, 0)
ResultRF2 <- cbind(test$PassengerId, ResultRF)
colnames(ResultRF2) <- c("PassengerId", "Survived")
write.csv(ResultRF2, file = "gender_submission.csv", row.names = TRUE)

# (4) knn

## Evaluate the results(using ROC curve)






