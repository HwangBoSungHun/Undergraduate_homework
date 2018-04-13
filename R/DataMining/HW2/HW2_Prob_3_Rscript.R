## Part3

#dev.off()
rm(list=ls())
# read data
dtcon <- read.table("Sham.data", header=TRUE)
dtcas <- read.table("PAB.data", header=TRUE)
colnames(dtcon) <- 'x'
colnames(dtcas) <- 'x'
trlabel1 <- rep('control', nrow(dtcon))
trlabel2 <- rep('case', nrow(dtcas))

#stack up data for convenience
dtall <- rbind(dtcon, dtcas)
labelall <- c(trlabel1, trlabel2)

labelallval <- rep(0, length(labelall))
labelallval[labelall == "control"] <- 0
labelallval[labelall == "case"] <- 1

id1 <- (labelallval == 1)
id0 <- (labelallval == 0)


#set the direction for testing
detcasek <- 1
if (mean(dtcon[,1]) > mean(dtcas[,1])) {
detcasek <- 2
}


#prepare threshold values
minv <- min( dtall[,1] )
maxv <- max( dtall[,1] )
TotLen <- 10
threshall <- seq(minv,maxv,length.out=TotLen)

tprall <- rep(0,TotLen) # Sensitivity
fnrall <- rep(0,TotLen) 
fprall <- rep(0,TotLen) # 1 - Specificity

for( i in 1:TotLen) {
 # to do some implementations here
  pred <- ifelse(dtall$x >= threshall[i], 1, 0)
  
  TP <- sum(pred == 1 & labelallval == 1)
  FP <- sum(pred == 1 & labelallval == 0)
  FN <- sum(pred == 0 & labelallval == 1)
  TN <- sum(pred == 0 & labelallval == 0)
  
  tprall[i] <- TP / (TP + FN) # Sensitivity
  fprall[i] <- FP / (FP + TN) # 1 - Specificity
  
  fnrall[i] <- FN / (TP + FN)
}



# saving the plot
#show ROC curve
plot(fprall, tprall, type="o", xlim=c(0,1), ylim=c(0,1), xlab="1-specificity", ylab="sensitivity", cex.lab=1.5)
#dev.copy(png,"myROC.png")
#dev.off()

