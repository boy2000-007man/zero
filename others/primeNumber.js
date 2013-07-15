#!/usr/bin/env node

// test prime number
var primeOrNot = function(n) {
    var i = 2;
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
};

var n = 1;
var t = 3;
var primeNumbers = [2];
for (n = 1; n < 100; t = t + 2) {
    if (primeOrNot(t) == 1) {
        primeNumbers.push(t);
        n++;
    }
}
var fs = require('fs');
outfile = "primeNumber";
fs.writeFileSync(outfile, primeNumbers.join(","));
