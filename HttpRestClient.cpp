/**
 * HttpRestClient.cpp
 *
 * Uses CppRestSDK to allow HTTP requests to be made to web services
 * to retrieve JSON data.
 *
 * @author Drioux Guidry
 * @version 08/23/2017
 */

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cpprest/json.h>
#include <stdlib.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


class HttpRestClient {

private:
	utility::string_t url;

public:
	inline HttpRestClient();
	inline json::value MakeRestRequest();
	inline void BuildUrl(utility::string_t firstPartOfUrl, utility::string_t name, utility::string_t key);
};


/**
 * Constructor
 */
HttpRestClient::HttpRestClient() {

	url = L"";
}

/**
 * Performs the HTTP request and returns the JSON data. Catches and prints
 * any errors, and then returns NULL.
 */
json::value HttpRestClient::MakeRestRequest() {

	try
	{
		// Create Client
		http_client client(url);

		// Make the request
		pplx::task<http_response> response = client.request(methods::GET);

		// Get the data in JSON
		http_response data = response.get();
		pplx::task<json::value> json = data.extract_json();

		return json.get();
	}
	catch (const http_exception& e) {
		// Print error.
		std::ostringstream ss;
		ss << e.what() << std::endl;
	}
	return NULL;
}


/**
 * Assembles the private URL to prepare for an HTTP request.
 */
void HttpRestClient::BuildUrl(utility::string_t firstPartOfUrl, utility::string_t flags, utility::string_t key) {
	this->url = firstPartOfUrl + flags + key;
}