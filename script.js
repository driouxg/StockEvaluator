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
//console.log(example1.factorial(6));


function read_line(cb) {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });
    rl.on('line', function (input) {
        cb(input)
        rl.close();
    });
}

try {
    read_line(function (input) {
        console.log(example1.factorial(input));
    });
}
catch (err) {
    console.log(err);
}

//read_line();

//console.log(example1.factorial(read_line()));

function function1() {
    // stuff you want to happen right away
    console.log('Welcome to My Console,');
}

function function2() {
    // all the stuff you want to happen after that pause
    console.log('Blah blah blah blah extra-blah');
}

// call the first chunk of code right away
function1();

// call the rest of the code and have it execute after 3 seconds
setTimeout(function2, 300000);