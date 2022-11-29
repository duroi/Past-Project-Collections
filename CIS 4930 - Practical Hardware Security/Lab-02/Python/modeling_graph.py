import matplotlib.pyplot as plt

##########################################################################
trials_10p = {'1':0.5637444, '2':0.5409333, '3':0.5056444,}
trial_10p = list(trials_10p.keys())
accuracy_10p = list(trials_10p.values())

fig = plt.figure(figsize = (10, 5))

# creating the bar plot
plt.bar(trial_10p, accuracy_10p, color ='darkgreen',
        width = 0.4)
 
plt.xlabel("Trials")
plt.ylabel("Accuracy")
plt.title("Accuracy of Trials with 10% Testing Data")
plt.savefig('Trials 10 Percent Testing.png')

##########################################################################

trials_30p = {'1':0.5380426, '2':0.5341571, '3':0.5392857,}
trial_30p = list(trials_30p.keys())
accuracy_30p = list(trials_30p.values())

fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(trial_30p, accuracy_30p, color ='forestgreen',
        width = 0.4)
 
plt.xlabel("Trials")
plt.ylabel("Accuracy")
plt.title("Accuracy of Trials with 30% Testing Data")
plt.savefig('Trials 30 Percent Testing.png')

##########################################################################


trials_50p = {'1':0.5798599, '2':0.5796599, '3':0.5331000,}
trial_50p = list(trials_50p.keys())
accuracy_50p = list(trials_50p.values())

fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(trial_50p, accuracy_50p, color ='limegreen',
        width = 0.4)
 
plt.xlabel("Trials")
plt.ylabel("Accuracy")
plt.title("Accuracy of Trials with 50% Testing Data")
plt.savefig('Trials 50 Percent Testing.png')

##########################################################################



trials_70p = {'1':0.5402666, '2':0.5846999, '3':0.5554666,}
trial_70p = list(trials_70p.keys())
accuracy_70p = list(trials_70p.values())

fig = plt.figure(figsize = (10, 5))
 
# creating the bar plot
plt.bar(trial_70p, accuracy_70p, color ='green',
        width = 0.4)
 
plt.xlabel("Trials")
plt.ylabel("Accuracy")
plt.title("Accuracy of Trials with 70% Testing Data")
plt.savefig('Trials 70 Percent Testing.png')