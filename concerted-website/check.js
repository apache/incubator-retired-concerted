var fs = require('fs'),
    path = require('path').resolve(process.cwd(), '');
    console.log(path);
function getDirectories(srcpath) {
  return fs.readdirSync(srcpath).filter(function(file) {
    return fs.statSync((path+"/"+file)).isDirectory();
  });
}
console.log(getDirectories(path));