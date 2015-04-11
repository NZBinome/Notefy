<?php

include 'Bridge.php';
include 'Follows.php';

$Followed = $_GET['Followed'];
$Follower = $_GET['Follower'];

$Follows1 = new Follows();
$Follows1->setFollower($Follower);
$Follows1->setFollowed($Followed);
date_default_timezone_set("Asia/Beirut");
$Follows1->setDate(date("Y-m-d H:i:s"));
$Follows1->insert();

?>