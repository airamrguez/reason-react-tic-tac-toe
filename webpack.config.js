const path = require('path');

module.exports = {
  entry: {
    tictactoe: './lib/js/src/index.js',
  },
  output: {
    path: path.join(__dirname, "public"),
    filename: '[name].js',
  },
};
