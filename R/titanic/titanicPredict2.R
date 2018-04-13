rm(list=ls())
library(dplyr)
library(caret)
library(DMwR)
library(ROCR)
library(randomForest)
library(vtreat)
setwd("~/Desktop/titanic")
train <- read.csv("train.csv")
test <- read.csv("test.csv")

fulldata <- rbind(train[,c(3, 5, 6, 7, 8, 10, 12)], test[,c(2, 4, 5, 6, 7, 9, 11)])
fulldata <- knnImputation(fulldata)
scaledData <- scale(fulldata[,c(3, 4, 5, 6)])
fulldata2 <- cbind(scaledData, model.matrix(~factor(Pclass) + Sex + Embarked, data = fulldata))
fulldata2 <- fulldata2[, c(1:4, 6:11)]

train1 <- as.data.frame(cbind(train$Survived, fulldata2[1:nrow(train),]))
colnames(train1) <-c("Survived", colnames(fulldata2))
preprocessedTrain1 <- as.data.frame(train1[1:600,])
valid1 <- as.data.frame(train1[601:nrow(train1),])
test1 <- as.data.frame(fulldata2[(nrow(train)+1):nrow(fulldata2),])

model.glm1 <- glm(Survived ~ ., family = "binomial", preprocessedTrain1)
summary(model.glm1)
model.pre1 <- predict(model.glm1, newdata = valid1, type = "response")

valid_result <- list()
for(i in 1:9) {
  valid_result[[i]] <- ifelse(model.pre1 > 0.1*i, 1, 0)
  print(i)
  print(confusionMatrix(valid_result[[i]], valid1$Survived))
}

predictTest <- predict(model.glm1, newdata = test1, type = "response")
testResult1 <- ifelse(predictTest > 0.6, 1, 0)
testResult2 <- cbind(test$PassengerId, testResult1)
colnames(testResult2) <- c("PassengerId", "Survived")
write.csv(testResult2, file = "gender_submission.csv", row.names = TRUE)

rowN <- as.integer(nrow(train1)/5) 

CV_k <- list()
CV_k[[1]] <- 1:rowN
CV_k[[2]] <- (rowN + 1):(rowN * 2)
CV_k[[3]] <- (rowN * 2 + 1):(rowN * 3)
CV_k[[4]] <- (rowN * 3 + 1):(rowN * 4)
CV_k[[5]] <- (rowN * 4 + 1):nrow(train1)

model_CV <- list() 
for(i in 1:5) {
  model_CV[i] <- glm(Survived ~ ., family = "binomial", train1[CV_k[[i]],])
}















