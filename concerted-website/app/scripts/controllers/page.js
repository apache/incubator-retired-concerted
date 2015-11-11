'use strict';

/**
 * @ngdoc function
 * @name concertedWebsiteApp.controller:MainCtrl
 * @description
 * # MainCtrl
 * Controller of the concertedWebsiteApp
 */
angular.module('concertedWebsiteApp')
.controller('MarkdownPagesCtrl', function ($scope,$routeParams,$http) {
    $scope.posturl=""+$routeParams.folder+"/"+$routeParams.name;
    $scope.pages;
    var loadlist= function(){
    $http.get($routeParams.folder+"/list.json").then(function(res){
        $scope.pages=res.data;
    });
    };
    loadlist();
})
.controller('FolderviewCtrl', function ($scope,$routeParams,$http) {
    $scope.pages;
    var loadlist= function(){
    $http.get($routeParams.folder+"/list.json").then(function(res){
        $scope.pages=res.data;
    });
    };
    loadlist();
});
