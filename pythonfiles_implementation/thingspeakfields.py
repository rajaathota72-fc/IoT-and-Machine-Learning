import requests
response = requests.get("https://api.thingspeak.com/channels/1116960/feeds.json?api_key=GKGTSTFQQFAWCE0L&results=2")
print(response.content)
data = response.json()
data_dictionary = dict(data)
print(data_dictionary["feeds"][1]["field1"])
print(data_dictionary["feeds"][1]["field2"])
print(data_dictionary["feeds"][1]["field3"])
print(data_dictionary["feeds"][1]["created_at"])