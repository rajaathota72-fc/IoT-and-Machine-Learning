import requests
path = "https://api.thingspeak.com/channels/1116960/feeds.json?api_key=GKGTSTFQQFAWCE0L&results=2"
response = requests.get(path)
data = response.json()
data_dictionary = dict(data)
temp = data_dictionary["feeds"][1]["field1"]
humi = data_dictionary["feeds"][1]["field2"]
noise = data_dictionary["feeds"][1]["field3"]
created_at = data_dictionary["feeds"][1]["created_at"]
data_e = [temp, humi, noise, created_at]
print(data_e)
if float(data_e[0])<26:
    import pywhatkit as kit
    kit.sendwhatmsg("+919912251001","The temperature is bit low. Dont forget to wear your winter clothing",22,39)




