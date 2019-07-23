# These two guides were helpful
# http://www.sthda.com/english/wiki/two-way-anova-test-in-r
# https://www.r-bloggers.com/raccoon-ch-2-4-3-way-anova/

# Info on how to interpret the QC plots
# https://data.library.virginia.edu/diagnostic-plots/

# Load in data
ai_data<- read.csv(file.choose())

# Get data structure
str(ai_data)

# Get number of cases per cell
table(ai_data$Modality, ai_data$OS, ai_data$Python)

# Run a full three-way ANOVA Model
fm <- aov(RT ~ Modality * OS * Python, data = ai_data)
summary(fm)

# Get a table of means for each term in the model
model.tables(fm,type="means")

# Get differences for each level of each factor
model.tables(fm,type="effects")

# Plot some QC figures (do you see outlier cases?)
# First figure is homogeneity of variances
# Second figure tests normality assumption
op <-  par(mfrow = c(2, 2))
plot(fm)

# Check the homogeneity of variance assumption
library(car)
leveneTest(RT ~ Modality * OS * Python, data = ai_data)

# Check the normality assumpttion
# Extract the residuals
aov_residuals <- residuals(object = fm)
# Run Shapiro-Wilk test
shapiro.test(x = aov_residuals )



# Get some descriptive statistics for the cells
require(dplyr)
group_by(ai_data, Modality, OS, Python) %>%
  summarise(
    count = n(),
    mean = mean(RT, na.rm = TRUE),
    sd = sd(RT, na.rm = TRUE)
  )

# Run some post-hoc comparisons
TukeyHSD(fm, which = "OS")
TukeyHSD(fm, which = "Python")
TukeyHSD(fm, which = "Modality")


library(ggplot2)


# Plot the cell means for the three way interaction
cell_means <- aggregate(RT ~ Modality + OS + Python, ai_data, mean)

ggplot(cell_means,
       aes(Modality, RT, linetype = Python, shape = Python, group = Python)) +
  geom_line() + geom_point(size = 3) +
  facet_wrap(~OS)