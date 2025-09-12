# Picture API from  https://api.lolicon.app/#/setu
# Pixiv API usage   https://blog.csdn.net/qq_42951560/article/details/109410214
import requests
import urllib3

# URL of API
url = "https://api.lolicon.app/setu/v2?r18=1"

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)
response = requests.get(url)
print('API respond success.')
if response.status_code == 200:
  try:
    json_response = response.json()
    data = json_response.get('data')
    if data is not None:
      real_data = data[0]
      urls = real_data['urls']
      if urls is not None:
        url = urls['original']
        headers = {'Referer': 'https://www.pixiv.net/'}
        res = requests.get(url, headers=headers, verify=False)
        print('Pixiv respond success.')
        with open(str(real_data['title']) + '.' + real_data['ext'], 'wb') as f:
            f.write(res.content)
        print('Generate success.')
      else:
        print("No \'urls\' in data.")
    else:
      print("No \'data\' in response.")
  except ValueError:
    print("Invalid JSON in response.")
else:
  print(f"Quest failed (status code = {response.status_code})")
