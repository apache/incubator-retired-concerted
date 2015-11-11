'use strict';

/**
 * @ngdoc function
 * @name concertedWebsiteApp.controller:ReleasesCtrl
 * @description
 * # ReleasesCtrl
 * Controller of the concertedWebsiteApp
 */
angular.module('concertedWebsiteApp')
  .controller('ReleasesCtrl', function ($scope,$http) {
    var baseurl="https://api.github.com/repos/apache/incubator-concerted"
    $scope.curr_page=1;
    $scope.releasedata=[];
    $scope.commitdata=[];
    $scope.loadreleases= function(){
      var url=baseurl+"/tags?page="+$scope.curr_page;
      $scope.curr_page=$scope.curr_page+1;
      $http.get(url)
      .then(function(response){
        $scope.releasedata=$scope.releasedata.concat(response.data);
        if (response.data.length!=0)
        { $scope.loadreleases();
        }

      });
    };
      $scope.loadcommits= function(){
        var url=baseurl+"/commits";
        console.log(url);
        $http.get(url)
        .then(function(response){
          $scope.commitdata=$scope.commitdata.concat(response.data);
        });

    };
    });
