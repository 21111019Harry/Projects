import pandas as pd
import numpy as np
import seaborn as sns import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from xgboost import XGBRegressor
from sklearn.ensemble import ExtraTreesRegressor
from sklearn.metrics import r2_score
from sklearn.preprocessing import StandardScaler
from sklearn import metrics
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import RandomizedSearchCV, train_test_split
###################################################################
################################################################
########### Her we Done Data Analysis Part ################
##########################################
df= pd.read_csv("AQI Data.csv")
print("Print Data")
print(df.head()) # to print the data this is pm 2.5 level data of banglore city
print("Check Null values")
print(df.isnull().sum()) # here we check any null value in our dataset but here 1
null value
print("Not Null Values")
df=df.dropna() # here we drop the null value bcz 1 null value not much effect
print(df.isnull().sum()) # then here print no null values
print("Print Unique values")
print(df.nunique()) #to check how many unique values in 1 variable
print("Datatypes")
print(df.dtypes)
print("Shape :",df.shape)
print(df.describe())
plt.figure(figsize=(9, 8))
plt.title("Check Values")
sns.histplot(df['PM 2.5'], color="red", label="100% Equities", kde=True,
stat="density", linewidth=0)
col= df.columns
print("Columns")
print(col) #here we print the coloumn list
for i in col:
 plt.figure(figsize=(9, 8))
 plt.title(i)
 sns.histplot(df[i], color="red", label="100% Equities", kde=True, stat="density",
linewidth=0)
pair_plot = sns.pairplot(df) # here we plot a pair plot
plt.suptitle("Pair Plot")
plt.show()
relation= df.corr()
top_corr_features = relation.index
plt.figure(figsize=(20,20))
g=sns.heatmap(df[top_corr_features].corr(),annot=True,cmap="RdYlGn")
plt.title("Correlation Heatmap")
plt.show()
print("Data Values")
print(df.head())
x = df.iloc[:, :-1] # here divide dataset x,x is independent variable
y = df.iloc[:, -1] # here divide dataset y,y is dependent variable
print("X,Y Values")
print(x.head()) # x head values
print(y.head()) # y head values
######## Here we use ensemble learning algorithm to more accuracy #########
#################################################################
model = ExtraTreesRegressor()
model.fit(x, y) # here we fit model of x and y train test data
print(model.feature_importances_)
feat_importances = pd.Series(model.feature_importances_, index=x.columns)
feat_importances.plot(kind='barh') # here we plot bar graph horizontal
plt.title("Feature Importances")
plt.show()
## hear we use standared scalar its use for scale the values
scale= StandardScaler()
x= scale.fit_transform(x) # here we fit x value
## here we split the train data and test data
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.2,
random_state=0)
print(y_train.shape) # here we see y train shape
##(764,) 764 sample and 1 coloumn asto AQI cha
print(X_test.shape) # here we see X train shape
##(328,8) 328 sample and 8 coloumn astat
###################################################################
###################################################################
##############################
##### Here we Done Model Building and Prediction using ML Models
###################################################
########## Here we use 1] XGBRegressor Model ###########
##################################################################
xg= XGBRegressor()
# No.of Estimators
n_estimators = [int(x) for x in np.linspace(start = 100, stop = 1200, num = 12)]
print(n_estimators)
# Different learning rate parameters
learning_rate = ['0.05','0.1', '0.2','0.3','0.5','0.6']
print(learning_rate)
# Maximum number of levels in tree
max_depth = [int(x) for x in np.linspace(5, 30, num = 6)]
print(max_depth)
#Subssample parameter values
subsample=[0.7,0.6,0.8]
print(subsample)
# Minimum child weight parameters
min_child_weight=[3,4,5,6,7]
print(min_child_weight)
param= {'n_estimators': n_estimators,
 'learning_rate': learning_rate,
 'max_depth': max_depth,
 'subsample': subsample,
 'min_child_weight': min_child_weight}
print(param)
xgb_random= RandomizedSearchCV(estimator = xg, param_distributions =
param,scoring='neg_mean_squared_error', n_iter = 100, cv = 5, verbose=2,
random_state=42, n_jobs = 1)
xgb_random.fit(X_train,y_train)
xgb_random.best_params_
xgr = XGBRegressor(subsample= 0.8,
n_estimators= 1100,
min_child_weight= 3,
max_depth= 30,
learning_rate= 0.05)
xgr.fit(X_train,y_train)
predictions=xgr.predict(X_test)
sns.histplot(y_test-predictions)
plt.scatter(y_test,predictions)
#from sklearn import metrics
print('MAE:', metrics.mean_absolute_error(y_test, predictions))
print('MSE:', metrics.mean_squared_error(y_test, predictions))
print('RMSE:', np.sqrt(metrics.mean_squared_error(y_test, predictions)))
#from sklearn.metrics import r2_score
print("r2_score is",r2_score(y_test, predictions)*100)
“”””””””
###################################################################
###################################################################
######## Here we use 2]RandomForestRegressor Model ############
###############################################
rf= RandomForestRegressor()
# Number of trees in random forest
n_estimators = [int(x) for x in np.linspace(start = 100, stop = 1200, num = 12)] #
here it start 100 and stop 1200 and it take 12 itteration
# Number of features to consider at every split
max_features = [1.0, 'sqrt']
# Maximum number of levels in tree
max_depth = [int(x) for x in np.linspace(5, 30, num = 6)]
# Minimum number of samples required to split a node
min_samples_split = [2, 5, 10, 15, 100]
# Minimum number of samples required at each leaf node
min_samples_leaf = [1, 2, 5, 10]
params = {'n_estimators': n_estimators, # this is dictionary params it stored
estimators etc
 'max_features': max_features,
 'max_depth': max_depth,
 'min_samples_split': min_samples_split,
 'min_samples_leaf': min_samples_leaf}
print(params)
# here we define the model with my rf estimators param_distributed...
rf_random = RandomizedSearchCV(estimator = rf, param_distributions =
params,scoring='neg_mean_squared_error', n_iter = 100, cv = 5, verbose=2,
random_state=42, n_jobs = 1)
rf_random.fit(X_train,y_train) # here we fit the x,y model
rf_random.best_params_
rf1= RandomForestRegressor(n_estimators= 500, # here we got the best
parameters in data
min_samples_split= 2,
min_samples_leaf=1,
max_features= 'sqrt',
max_depth=15)
rf1.fit(X_train,y_train) # here we fit the x,y train data
ypred= rf1.predict(X_test) # here we predict test data
#from sklearn import metrics
print('MAE:', metrics.mean_absolute_error(y_test, ypred))
print('MSE:', metrics.mean_squared_error(y_test, ypred))
print('RMSE:', np.sqrt(metrics.mean_squared_error(y_test, ypred)))
print("Final Prediction is:")
## here we got the final AQI prediction
## here we use r2 score function for performance of regression model by
calculating r2 score and use for predict the air quality index accurately
print(r2_score(y_test, ypred)*100)
“”””””
