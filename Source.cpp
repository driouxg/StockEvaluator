#include <nan.h>
#include <node.h>
#include <v8.h>
#include <cmath>
#include "HttpRestClient.cpp"

//Command K:\Users\drioux\Desktop\Node\node\Debug\node.exe
//Command arguments script.js
//Working Directory ..

//Compile using command: node-gyp configure rebuild --nodedir="K:\Users\drioux\Desktop\Node\node"
//Make sure you are in the directory that contains the binding.gyp file before you issue the above command in terminal

/**
 * BASIC DATA TYPE CONVERSION EXAMPLES
 *
 * v8::FunctionCallbackInfo<v8::Value> to std::string
 *--------------------------------------------------------
 * v8::String::Utf8Value param1(args[0]->ToString());
 * std::string from = std::string(*param1);
 * 
 *
 * 
 */




/**
 * Makes a RESTful call using the CPPRestSDK and returns a particular element from the requested JSON.
 */
void MakeRestfulCall_impl(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = args.GetIsolate();
	HttpRestClient *client = new HttpRestClient();

	// Convert the string v8 string to std::string
	v8::String::Utf8Value param1(args[0]->ToString());
	std::string from = std::string(*param1);

	// Convert the std::string to utility string
	utility::string_t url = utility::conversions::to_string_t(from);

	try
	{
		client->BuildUrl(url, L"", L"");
		json::value& jobj = client->MakeRestRequest();																			// Make the HTTP request
		std::string date = utility::conversions::to_utf8string(jobj.at(U("datatable")).at(U("data"))[0][0].as_string());		// Retreive a data value from the JSON
		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, date.c_str()));												// Set the return value
	}
	catch (const http_exception& e) {
		std::ostringstream ss;
		ss << e.what() << std::endl;
	}
}

/**
 *
 */
void MakeRestfulCall(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::Isolate* isolate = args.GetIsolate();

	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, MakeRestfulCall_impl);
	v8::Local<v8::Function> fn = tpl->GetFunction();

	// omit this to make it anonymous
	fn->SetName(v8::String::NewFromUtf8(isolate, "theFunction"));

	args.GetReturnValue().Set(fn);
}

/**
 * Returns the result of a factorial calculation
 */
static int factorial_impl(int n) {
	int ret = 1; for (int i = 1; i <= n; ++i) { ret *= i; } return ret;
}



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







/**
 * Initialize all nodes
 */
void Init(v8::Local<v8::Object> exports) {
	NAN_EXPORT(exports, factorial);
	//exports->Set(Nan::New("factorial").ToLocalChecked(),
	//    Nan::New<v8::FunctionTemplate>(factorial)->GetFunction());

	NODE_SET_METHOD(exports, "MakeRestfulCall", MakeRestfulCall);
}

//Export the node using the Init function, and giving it the name "Source"
NODE_MODULE(Source, Init);