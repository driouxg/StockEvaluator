// note that the compiled addon is placed under following path
const example1 = require('./build/Release/Source');
const readline = require('readline');

//const rl = readline.createInterface({
//    input: process.stdin,
//    output: process.stdout
//});
//
//rl.question('What do you think of Node.js? ', (answer) => {
//    // TODO: Log the answer in a database
//    console.log(`Thank you for your valuable feedback: ${answer}`);
//
//    rl.close();
//});
//
var url = "https://www.quandl.com/api/v3/datatables/WIKI/PRICES.json?ticker=FB&qopts.columns=date,open&api_key=yehvpJU2HiME7iWE1aKQ";

try {
    console.log(example1.factorial(5));
    const fn = example1.MakeRestfulCall(url);
    console.log(fn(url));
}
catch(err) {
    console.log(err);
}

function function1() {
    // stuff you want to happen right away
    console.log('Welcome to My Console,');
}

// call the first chunk of code right away
function1();


// call the rest of the code and have it execute after 3 seconds
setTimeout(function1, 300000);