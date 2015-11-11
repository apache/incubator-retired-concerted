var fs = require("fs");
var _=require("lodash");

Object.deepExtend = function(destination, source) {
  for (var property in source) {
    if (typeof source[property] === "object" &&
     source[property] !== null ) {
      destination[property] = destination[property] || {};
      arguments.callee(destination[property], source[property]);
    } else {
      destination[property] = source[property];
    }
  }
  return destination;
};

path = require('path').resolve(process.cwd(), 'app');
function getDirectories(srcpath) {
  return fs.readdirSync(srcpath).filter(function(file) {
    return fs.statSync((path+"/"+file)).isDirectory();
  });
}

var folders=[];
dirs=getDirectories(path);
for(dir in dirs){
var folderobj={};
if(dirs[dir][0]!='.'){
  folderobj.url=dirs[dir];
    folders.push(folderobj);
  }
}
console.log(folders);
for(folder in folders){
  console.log("Searching "+folders[folder].url+"...");
  var url="app/"+folders[folder].url;
  files=fs.readdirSync(url);
    var fileobj={};
    var filelist=[];
    files.forEach(function (file){
      if((/\.(md)$/i).test(file)){
        console.log("Indexing "+file);
        if (folders[folder].url=="news" || folders[folder].url=="blog"){
          fileobj.url=folders[folder].url+"/"+file;
          var res=file.split('-');
          fileobj.year=res[0];
          fileobj.month=res[1];
          fileobj.date=res[2];
          fileobj.title=((res[3].replace(/_/g,' ')).split("."))[0];
        }
      else{
          fileobj.url=folders[folder].url+"/"+file;
          fileobj.title=file.split(".")[0];
        }
      var temp={};
      filelist.push(Object.deepExtend(temp,fileobj));
      }
    });
    console.log("Index for "+folders[folder].url+"\n"+filelist);
    fs.writeFile("app/"+folders[folder].url+"/list.json",JSON.stringify(filelist),function(err){
      if(err){
        console.log("Error writing index for "+folders[folder].url+"\n"+err);
      }
    });
    if(folders[folder].url=="news"||folders[folder].url=="blog"){
      var archive=_.groupBy(filelist, function(n) {
      return n.year;
      });
      console.log("Archive for "+folders[folder].url+"\n"+archive);
      fs.writeFile("app/"+folders[folder].url+"/archive.json",JSON.stringify(archive),function(err){
        if(err)
          console.log(err);
      });
    }
    console.log(filelist);
    filelist=[];
    console.log(filelist);
};

