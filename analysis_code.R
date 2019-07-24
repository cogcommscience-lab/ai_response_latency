
# These two guides were helpful
# http://www.sthda.com/english/wiki/two-way-anova-test-in-r
# https://www.r-bloggers.com/raccoon-ch-2-4-3-way-anova/

# Info on how to interpret the QC plots
# https://data.library.virginia.edu/diagnostic-plots/

# Load packages
library(dplyr)
library(ggplot2)
library(ggridges)
library(plotrix)
library(car)

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
leveneTest(RT ~ Modality * OS * Python, data = ai_data)

# Check the normality assumpttion
# Extract the residuals
aov_residuals <- residuals(object = fm)
# Run Shapiro-Wilk test
shapiro.test(x = aov_residuals )

# Get some descriptive statistics for the cells

dsummary<-group_by(ai_data, Modality, OS, Python) %>%
  summarise(
    count = n(),
    mean = mean(RT, na.rm = TRUE),
    sd = sd(RT, na.rm = TRUE),
    se = std.error(RT, na.rm = TRUE),
    ci95 = 1.96*(std.error(RT, na.rm=TRUE))
  )
dsummary

# Run some post-hoc comparisons
TukeyHSD(fm, which = "OS")
TukeyHSD(fm, which = "Python")
TukeyHSD(fm, which = "Modality")


# Make raincloud plots for main effects

ggplot(ai_data, aes(x=RT, y=OS, color=OS)) +
  geom_density_ridges(
    jittered_points = TRUE, position = "raincloud",
    alpha = 0.7, scale = 0.7
  ) +
  labs(title = "Raincloud Plot For Operating System")

ggplot(ai_data, aes(x=RT, y=Python, color=Python)) +
  geom_density_ridges(
    jittered_points = TRUE, position = "raincloud",
    alpha = 0.7, scale = 0.7
  ) +
  labs(title = "Raincloud Plot For Python Version")

ggplot(ai_data, aes(x=RT, y=Modality, color=Modality)) +
  geom_density_ridges(
    jittered_points = TRUE, position = "raincloud",
    alpha = 0.7, scale = 0.7
  ) +
  labs(title = "Raincloud Plot For Modality")

# Plot two-way interactions
# See https://homepage.divms.uiowa.edu/~luke/classes/STAT4580/boxetc.html

ggplot(ai_data, aes(x=RT, y=Python, group=interaction(OS, Python), fill=OS)) +
  geom_density_ridges(
    jittered_points = TRUE, position = "raincloud",
    alpha = 0.7, scale = 0.6
  ) +
  labs(title = "Raincloud Plot For Operating System by Python Interaction")

ggplot(ai_data, aes(x=RT, y=Modality, group=interaction(OS, Modality), fill=OS)) +
  geom_density_ridges(
    jittered_points = TRUE, position = "raincloud",
    alpha = 0.7, scale = 0.6
  ) +
  labs(title = "Raincloud Plot For Operating System by Modality Interaction")


# Plot the three way interaction with 95% CI error bars

ggplot(dsummary,
       aes(Modality, mean, linetype = Python, shape = Python, group = Python, color=Python)) +
  geom_line() + geom_point(size = 3) +
  facet_wrap(~OS) +
  geom_errorbar(aes(ymin=mean-ci95, ymax=mean+ci95), width=.2) +
  labs(title = "Three Way Interaction",
       subtitle = "Error Bars Represent 95% CI of the Mean")