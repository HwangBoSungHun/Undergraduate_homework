library(dplyr)
#dev.off()
## Part1
setwd("~/Desktop/3-1/DataMining/HomeWork/HW2")
train_data <- read.csv("HWtrain.data.txt", header = FALSE)
test_data <- read.csv("HWtest.data.txt", header = FALSE)

train <- train_data[, -1]
train_y <-train_data[, 1]
test <- test_data[, -1]

train_norm <- scale(train)

train.pr <- princomp(train_norm)
summary(train.pr)

#Creating a biplot
biplot(train.pr)

#Getting proportion of variance for a scree plot
train.pr.var <- train.pr$sdev^2
pve <- train.pr.var / sum(train.pr.var)
plot(pve, xlab = "Principal Component", 
     ylab = "Portion of Variance Explaine",
     ylim = c(0, 1), type = "b")

# (a) When we use the first two principle components, 
# how much information of the total do we use? 
sprintf("%.2f%%", sum(pve[1:2]) * 100)

# (b) Find the top-three original variables among 
# the 13 that contributed to the construction 
# of the first principle component. 
abs(train.pr$loadings[, 1]) %>% 
  sort(decreasing = TRUE) %>%
  head(3)

# (c) Draw a plot of the 1st scores (on the X axis) and the 2nd scores 
# (on the Y axis) of the descriptive values in HWtrain.data.txt together
# with the wine qualities and similarly transformed score values of the 
# five future observations in HWtest.data.txt.  Then try to predict the 
# wine quality of each of the five future observations.

plot(train.pr$scores[,1], train.pr$scores[,2], pch = 20,
     xlab = "PC1", ylab = "PC2", col = train_y, main = "Wine quality ")
text(train.pr$scores[,1], train.pr$scores[,2], 
     labels = train_y, pos = 4, col = train_y, cex = 0.6)

test_norm <- scale(test)
test.pr <- as.matrix(test_norm) %*% as.matrix(train.pr$loadings[, 1:2])
points(test.pr[,1], test.pr[,2], col = "blue", pch =15)
text(test.pr[,1], test.pr[,2],  
     labels = 1:5, pos = 4, col = "blue", cex = 1.2)
#png("predictWineQuality.png", width=400, height=300, pointsize=13)
#dev.off()

## Part2
library(readxl)
library(caret)

data2 <- read_xlsx("HW2_data_2.xlsx")
data2$Y <- as.factor(data2$Y)
data2_X <- data2$Xun
data2_norm_X <- (data2_X - min(data2_X)) / (max(data2_X) - min(data2_X))
data2_norm <- data2
data2_norm$Xun <- data2_norm_X

data2_norm_1 <- data2_norm # cut-off value 0.4
data2_norm_1$Y <- as.factor(ifelse(data2_norm$Xun >= 0.4, 1, 0)) 

data2_norm_2 <- data2_norm # cut-off value 0.5
data2_norm_2$Y <- as.factor(ifelse(data2_norm$Xun >= 0.5, 1, 0)) 

data2_norm_3 <- data2_norm # cut-off value 0.4
data2_norm_3$Y <- as.factor(ifelse(data2_norm$Xun >= 0.6, 1, 0)) 

#confusionMatrix(data2_norm_1$Y, data2_norm$Y)
#confusionMatrix(data2_norm_2$Y, data2_norm$Y)
#confusionMatrix(data2_norm_3$Y, data2_norm$Y)
confusionMat <- function(pred, actual)
{
  TP <- sum(pred$Y == 1 & actual$Y == 1)
  FP <- sum(pred$Y == 1 & actual$Y == 0)
  FN <- sum(pred$Y == 0 & actual$Y == 1)
  TN <- sum(pred$Y == 0 & actual$Y == 0)
  
  confuMat <- matrix(c(TP, FP, FN, TN), byrow = TRUE, nrow = 2, ncol = 2)
  confuMat_df <- data.frame(confuMat, row.names = c("pred_True(1)", "pred_False(0)"))
  colnames(confuMat_df) <- c("act_True(1)", "act_False(0)")
  
  confuMat_df
  
  accur <- (TP + TN) / (TP + FP + FN + TN)
  sensi <- TP / (TP + FN)
  speci <- TN / (FP + TN)
  preci <- TP / (TP + FP)
  result.list <- list(ConfusionMatrix = confuMat_df, Accuracy = accur, 
                      Sensitivity = sensi, Specificity = speci, 
                      Precision = preci) 
  return(result.list)
}

confusionMat(data2_norm_1, data2_norm)
confusionMat(data2_norm_2, data2_norm)
confusionMat(data2_norm_3, data2_norm)



