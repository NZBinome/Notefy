<?php 

include 'User.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'Melody.php';
include 'CreateFeed.php';
include 'ShareFeed.php';
include 'Share.php';
include 'Follows.php';

$UserId = $_GET['UserId'];
$Follower = $_GET['Follower'];
$User1 = new User($UserId);
$Follows1 = new Follows($Follower,$UserId);

$ToSend = "<Root>";
$ToSend = $ToSend . "<Header>";
$ToSend = $ToSend . $User1->toXML();
$ToSend = $ToSend . $Follows1->toXML();
$ToSend = $ToSend . "</Header>";
$ToSend = $ToSend . "</Root>";
echo $ToSend;

?>