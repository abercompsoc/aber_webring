# AberWebRing

## What is a webring?
A [webring](https://en.wikipedia.org/wiki/Webring) is a collection of websites in a circular structure, each one has left and right buttons leading to the next websites in the ring, its essentially just a fun easter-egg to hide on your site. It lets people in your community see your site and gives you a way to see other peoples. We set it up to encourage our members to build and host personal websites, if you don't have one, you should give it a go!

## How does this work?
The code here is a service we have running on a server at [aberwebr.ing](https://aberwebr.ing). It holds links to each website and an identifier for each. Your website then just makes a request to it with its identifier and a statement whether to go left or right, it'll then redirect you to the next site. 

```https://aberwebr.ing/AlicesWebsite/left```

## Joining
To join the webring, read the criteria section below, then just create a pull request adding yourself to the pages.csv file. Then add the webring buttons somewhere on your site. You __must__ have a left and right button, and its also common practise to have a central button that goes to [the webrings index page](https://aberwebr.ing). If in doubt, look at how the other members implement theirs!

## Criteria
If you're wanting to add yourself to this, please make sure your page doesnt contain any hateful content or anything inappropriate. 

This is up to your discretion but just ask yourself whether other people would be okay linking their website (possibly a portfolio or recruiter facing site) to yours, if theres a chance they wouldnt then best avoid it.

Make sure your website represents you! This is meant for personal sites, not projects or adverts.

## Building this code + details on the csv file
If you want to use this code yourself for your own webring (which you defo should do!). Build it with cmake and give it the location of the csv file of pages as an argument when running it.

You'll need a few things before you can build it:
- Asio development headers (1.10.9 or later)
- OpenSSL
- CMake

Also note, the CSV file follows this format:

```unique identifier,website url,email```

also also note, the program doesnt remove any whitespace so only put spaces where you want them e.g. not after a comma

## Important things!
- We are unaffiliated with the universtity, this is a student/alumni run project.
- If you want anything taken off the webring, raise an issue and we'll get on it as soon as we see it :)
