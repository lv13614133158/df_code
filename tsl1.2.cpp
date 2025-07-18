#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <curl/curl.h>
#include <iostream>

int main() {
    // 初始化 CURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return 1;
    }

    // 设置请求选项
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com"); // 替换为你的目标URL
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);         // 跟随重定向

    // 启用证书验证（默认启用）
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // 验证对方证书
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // 验证主机名

    // 如果需要，加载CA证书
    curl_easy_setopt(curl, CURLOPT_CAINFO, "/home/nvidia/git/df/rootcertclient.pem"); // CA证书路径

    // 如果需要，加载客户端证书和私钥
    curl_easy_setopt(curl, CURLOPT_SSLCERT, "/home/nvidia/git/df/TBOX-YYZS.pem"); // 客户端证书
    curl_easy_setopt(curl, CURLOPT_SSLKEY, "/home/nvidia/git/df/TBOX-YYZS.key");   // 客户端私钥

    // 执行请求
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
    }

    // 清理
    curl_easy_cleanup(curl);
    return 0;
}
