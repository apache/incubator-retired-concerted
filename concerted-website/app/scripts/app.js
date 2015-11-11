'use strict';

/**
 * @ngdoc overview
 * @name concertedWebsiteApp
 * @description
 * # concertedWebsiteApp
 *
 * Main module of the application.
 */
angular
  .module('concertedWebsiteApp', [
    'ngAnimate',
    'ngCookies',
    'ngResource',
    'ngRoute',
    'ngSanitize',
    'ngTouch',
    'angular-loading-bar',
    'gsmarkdown'
  ])
  .config(function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        // controller: 'MainCtrl',
        // controllerAs: 'main',
        // title: "Concerted|Home"
      })
      .when('/releases', {
        templateUrl: 'views/releases.html',
        controller: 'ReleasesCtrl',
        controllerAs: 'releases',
        // title: "Concerted|Releases"
      })
      .when('/news', {
        templateUrl: 'views/news.html',
        controller: 'PostsCtrl',
        // title: "Concerted|News"
      })
      .when('/blog', {
        templateUrl: 'views/news.html',
        controller: 'BlogCtrl',
        // title: "Concerted|News"
      })
      .when('/contribute', {
        templateUrl: 'views/contribute.html',
        // title: "Concerted|Get Involved"
      })
      .when('/blog/:year', {
        templateUrl: 'views/news.html',
        controller: 'YearlyBlogCtrl'
        // controllerAs: 'yaer',
        // title: "Concerted|Get Involved"
      })
      .when('/pages/:type/:year/:month/:date/:title', {
        templateUrl: 'views/post.html',
        controller: 'OnepostCtrl'
        // controllerAs: 'yaer',
        // title: "Concerted|Get Involved"
      })
      .when('/markdown-pages/:folder/:name', {
        resolve: {
        check: ["$route", "$http", "$location", function($route, $http, $location){
        return $http.get($route.current.params.folder +"/"+$route.current.params.name).success(function(res){
        return true;
        }).error(function(res){
        return $location.path("/404");
        });
        }]
        },
        templateUrl: 'views/page.html',
        controller: 'MarkdownPagesCtrl'

        // controllerAs: 'yaer',
        // title: "Concerted|Get Involved"
      })
      .when('/markdown-pages/:folder/', {
        resolve: {
        check: ["$route", "$http", "$location", function($route, $http, $location){
          console.log($route.current.params.folder+"/list.json");
        return $http.get($route.current.params.folder+"/list.json").success(function(res){
        return true;
        }).error(function(res){
        return $location.path("/404");
        });
        }]
        },
        templateUrl: 'views/folderview.html',
        controller: 'FolderviewCtrl'
      })
      .when('/404', {
        templateUrl: '/404.html'
      })
      .otherwise({
        redirectTo: '/'
      });
  });
