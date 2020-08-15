import pandas as pd
df = pd.read_csv("weather_data_train_labels.csv",parse_dates =['datetime'],
                           sep =';',decimal=',',infer_datetime_format=True)
print(df.dtypes)
temp_df = df[["datetime","U_mu"]]
print()
from statsmodels.tsa.seasonal import seasonal_decompose
from matplotlib import pyplot as plt
# ETS decomposition
result = seasonal_decompose(temp_df["U_mu"],model='multiplicative',extrapolate_trend='freq',freq=365)
result.plot()
#plt.show()
from statsmodels.tsa.statespace import sarimax
model = sarimax.SARIMAX(temp_df["U_mu"],order = (0, 1, 1),seasonal_order =(2, 1, 1, 12))
result = model.fit()
print(result.summary())
pred = result.get_prediction(start=pd.to_datetime('2012-09-20'),dynamic=False)
pred_ci = pred.conf_int()
print(pred,pred_ci)


