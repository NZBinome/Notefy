<?php

include 'Toolkit.php';
include 'Bridge.php';
include 'Melody.php';
include 'Follows.php';
include 'Share.php';
include 'User.php';
include 'Comment.php';
include 'Applause.php';


$Toolkit1 = new Toolkit();
//$Toolkit1->getMelodiesOfUser(1);
$Toolkit1->getFollowers(2);
//$Toolkit1->getFollowed(1);




//$User1 = new User(2);
//$User1->display();

?>