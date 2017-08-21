#include <nan.h>
#include <cmath>
#include "HttpRestClient.cpp"

#define EMPTY L""
#define QUANDL_TEST_URL L"https://www.quandl.com/api/v3/datatables/WIKI/PRICES.json?ticker=FB&qopts.columns=date,open&api_key=yehvpJU2HiME7iWE1aKQ"

using namespace Nan;

/**
 * Returns JSON data 
 */
static std::string MakeRestfulCall_impl() {
	HttpRestClient *client = new HttpRestClient();

	client->url = QUANDL_TEST_URL;

	json::value& jobj = client->MakeRestRequest();
	try
	{
		std::string json = utility::conversions::to_utf8string(jobj.at(U("name")).as_string());
		return json;
	}
	catch (const http_exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl;
	}
	return NULL;
}

/**
 * Returns the result of a factorial calculation
 */
static int factorial_impl(int n) {
	int ret = 1; for (int i = 1; i <= n; ++i) { ret *= i; } return ret;
}

//Compile using command: node-gyp configure rebuild --nodedir="K:\Users\drioux\Desktop\Node\node" while in the working directory of this project addon




NAN_METHOD(factorial) {
	//void export_factorial(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() != 1) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}

	if (!info[0]->IsNumber()) {
		Nan::ThrowTypeError("Argument should be a number");
		return;
	}

	double arg0 = info[0]->NumberValue();
	v8::Local<v8::Number> num = Nan::New(factorial_impl(static_cast<int>(arg0)));

	info.GetReturnValue().Set(num);
}

NAN_METHOD(MakeResfulCall) {
	v8::MaybeLocal<v8::String> json = Nan::New(MakeRestfulCall_impl());
	info.GetReturnValue().Set(Nan::To<v8::String>(info[0]).ToLocalChecked());
}


/**
 * Initialize all nodes
 */
void Init(v8::Local<v8::Object> exports) {
	NAN_EXPORT(exports, factorial);
	//exports->Set(Nan::New("factorial").ToLocalChecked(),
	//    Nan::New<v8::FunctionTemplate>(factorial)->GetFunction());

	Nan::Set(target
		, Nan::New<v8::String>("MakeRestfulCall").ToLocalChecked()
		, Nan::New<v8::FunctionTemplate>(MakeRestfulCall)->GetFunction()
	);
}



//Export the node along with the name of the node
NODE_MODULE(Source, Init)