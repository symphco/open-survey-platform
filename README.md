# Release Notes

This Open Survey Platform was developed and launched in March 2015. The development of the platform, visualizations and dashboards was conducted by multiple development firms based in the United States and in the Philippines. This Open Survey Platform ("white-label version") is being released via GitHub under an Open Source initiative to assist other countries and providers to advance the discussion in building the practice of Open Data. 

The Open Survey Platform while sufficiently advanced in terms of programming and design in 2014, it should be noted that the pace of technology is rapid and there are numerous updates and fixes available for this platform. To this end there are many opportunities to further develop the platform with functional and aesthetic enhancements. 

That said, the initiative abides by the aphorism "Perfect is the enemy of good", and the code is released with the hope that it is a good (not perfect) starting point for others to learn from and improve in their Open Data initiatives as well as to contribute back to this repository so that the greater community can continue to benefit. 

# Site Audit

Prior to release a site audit was perfromed in December 2015 by a third-party to assess the structure, issues and recommendations for future development. As this platform is comprised of two Drupal instances, there are two site audit reports. They are available within the repo and via a direct link: https://github.com/opengovt/open-survey-platform/blob/master/2015-12-18-Survey-Builder-Site-Audit.pdf
https://github.com/opengovt/open-survey-platform/blob/master/2015-12-18-Survey-Platform-Site-Audit.pdf

We strongly encourage that these recommendations be followed for all who would use this platform.

# User Guides and Features

User Guides and Features: https://opengovt.github.io/open-survey-platform/

# Mobile Application (Android)

This web based platform works in collaboration with the mobile survey tool: https://github.com/opengovt/mobile-android-survey-app


---


# Developer Documentation


## Setting up the Platform


This platform is built on two packages. Each package is powered by the Drupal CMS, and connects with each other using the Drupal Services module. To learn more about Drupal, visit: https://www.drupal.org/


Each package contains two parts. (1) The code base and (2) the database dump. The database dump needs to be imported into a MySQL database and the code base settings configured.


* Importing the database from phpMyAdmin: https://www.drupal.org/node/81995
   
* Importing the database from command line: https://www.drupal.org/node/345225





## Admin credentials for the each package

 * Username: admin
 * Password: 123456

 _Note: "Change password before running the site in production mode."_



