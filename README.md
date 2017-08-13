# Release Notes

Open Survey is a dynamic survey platform which allows for the creation of mobile flash surveys (short surveys using Open Data Kit) combined with the collection and aggregation of the survey information in real-time for display in a web-based platform generating interactive data visualizations and dashboards. The original version was used in the Education Sector to dynamically collect the Geo-location and attribute information of primary and secondary schools. Open Survey was developed through multiple development firms based in the United States and in the Philippines. Open Survey ("white-label version") is being released via GitHub under an Open Source Initiative to assist other countries, practitioners and developer and providers to advance the discussion in building the practice of Open Government Accountability Platforms.

It is important to note, that while the platform is sufficiently advanced in terms of programming and design the pace of technology is rapid and there are numerous updates and fixes available for this platform. To this end there are many opportunities to further develop the platform with functional and aesthetic enhancements. That said, this initiatives (alongside those in this GitHub account) abides by the aphorism "Perfect is the enemy of good", and the code is released with the view that it is a good (not perfect) starting point for others to learn from and improve in their own initiatives as well as to contribute back to this repository so that the greater community can continue to benefit.

# Site Audit

Prior to release a site audit was performed in December 2015 by a third-party to assess the structure, issues and recommendations for future development. As this platform is comprised of two Drupal instances, there are two site audit reports. They are available within the repository and via a direct link: https://github.com/symph-team/open-survey-platform/blob/master/2015-12-18-Survey-Builder-Site-Audit.pdf
https://github.com/symph-team/open-survey-platform/blob/master/2015-12-18-Survey-Platform-Site-Audit.pdf

We strongly encourage that these recommendations be followed for all who would use this platform.

# User Guides and Features

User Guides and Features: https://symph-team.github.io/open-survey-platform/

# Mobile Application (Android)

This web based platform works in collaboration with the mobile survey tool: https://github.com/symph-team/mobile-android-survey-app


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



