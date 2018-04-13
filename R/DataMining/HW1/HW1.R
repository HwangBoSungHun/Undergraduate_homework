library(dplyr)
library(plot3D)
library(caret)
library("titanic")

#Part1
setwd("~/Desktop/3-1/DataMining/HW1")
carData <- read.table("data_1.txt", header = TRUE)

scatter3D(x = carData$KM, y = carData$Weight, z = carData$Price, xlab = "KM", ylab = "Weight", zlab = "Price")
title("3D scatter plot about Car")

# Part2
# (1) 5-fold cross validation
set.seed(42)

# modelcv1: Price ~ KM + HP + CC
modelcv1 <- train(Price ~ KM + HP + CC, data = carData,  method = "lm",
  trControl = trainControl(method = "cv", number = 5, verboseIter = TRUE))

# modelcv2: Price ~ KM + HP + CC + Doors
modelcv2 <- train(Price ~ KM + HP + CC + Doors, data = carData,  method = "lm",
                trControl = trainControl(method = "cv", number = 5,verboseIter = TRUE))
# modelcv3: Price ~ KM + HP + CC + Doors + Quarterly_Tax
modelcv3 <- train(Price ~ KM + HP + CC + Doors + Quarterly_Tax, data = carData,  method = "lm",
                trControl = trainControl(method = "cv", number = 5,verboseIter = TRUE))


# (2) randomized 80% training-20% testing validation
rows <- sample(nrow(carData))
newcarData <- carData[rows,]
split <- round(nrow(carData) * 0.8)

train <- newcarData[1:split,]
test <- newcarData[(split+1):nrow(newcarData),]

"Train dataset' s sd:"
sd(train$Price)
# model1: Price ~ KM + HP + CC
model1 <- lm(Price ~ KM + HP + CC, data = train)
predict1 <- predict(model1, test)
error1 <- predict1 - test$Price
sqrt(mean(error1 ^ 2))

tot_error <- test$Price - mean(test$Price)
sstot_error <- sum(tot_error^2)
(rsquared_error1 <- 1 - sum(error1^2)/sstot_error)

# model2: Price ~ KM + HP + CC + Doors
model2 <- lm(Price ~ KM + HP + CC + Doors, data = train)
predict2 <- predict(model2, test)
error2 <- predict2 - test$Price
sqrt(mean(error2 ^ 2))

(rsquared_error2 <- 1 - sum(error2^2)/sstot_error)
# model3: Price ~ KM + HP + CC + Doors + Quarterly_Tax
model3 <- lm(Price ~ KM + HP + CC + Doors + Quarterly_Tax, data = train)
predict3 <- predict(model3, test)
error3 <- predict3 - test$Price
sqrt(mean(error3 ^ 2))
(rsquared_error3 <- 1 - sum(error3^2)/sstot_error)
### Add more variable...
modelcv4 <- train(Price ~ Age_08_04 + KM + HP + Met_Color + Automatic + CC 
                  + Doors + Quarterly_Tax, data = carData,  method = "lm", 
                  trControl = trainControl(method = "cv", number = 5,verboseIter = TRUE))


model4 <- lm(Price ~ Age_08_04 + KM + HP + Met_Color + Automatic + CC 
             + Doors + Quarterly_Tax, data = train)
predict4 <- predict(model4, test)
error4 <- predict4 - test$Price
sqrt(mean(error4 ^ 2))
(rsquared_error4 <- 1 - sum(error4^2)/sstot_error)

# Part3
data(titanic_train)
str(titanic_train)

titanic_train_original <- titanic_train

dropNames <- c("Name", "Ticket", "Cabin", "PassengerId")
toSelect <- !(names(titanic_train_original) %in% dropNames)
titanic_train2 <- titanic_train_original[, toSelect]
titanic_train3 <- titanic_train2
titanic_train3$Pclass <- as.factor(titanic_train2$Pclass)

newcol <- model.matrix( ~ Sex + Pclass + Embarked, data = titanic_train3)[,-1]

titanic_train4 <- titanic_train3 %>%
  select(-Sex, -Pclass, -Embarked) %>%
  cbind(newcol)

# EDA
summary(titanic_train4)
titanic_train5 <- titanic_train4[which(!is.na(titanic_train4$Age)),] # NA delete
train5_live <- titanic_train5[which(titanic_train5$Survived == 1),] # Survivor
train5_death <- titanic_train5[-which(titanic_train5$Survived == 1),] # Dead
library(corrplot)
corrplot(cor(titanic_train5))

par(mfrow = c(1, 2))
boxplot(train5_death$Age, train5_live$Age, main = "Age")
boxplot(train5_death$Fare, train5_live$Fare, main = "Fare")

library(ggplot2)
ggplot(data = titanic_train3, mapping = aes(x = Survived, fill = Sex)) + geom_bar()  
mosaicplot(data = titanic_train3, Survived ~ Pclass, main = "Survival by Pclass")
mosaicplot(data = titanic_train3, Survived ~ Embarked, main = "Survival by Embarked")

