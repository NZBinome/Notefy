<?php 

include 'User.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'Melody.php';
include 'Follows.php';

$UserId = $_GET['UserId'];
$Follower = $_GET['Follower'];
$User1 = new User($UserId);
$Toolkit1 = new Toolkit();
$Follows1 = new Follows($Follower,$UserId);

$ToSend = "<Root>";
$ToSend = $ToSend . $User1->toXML();

$Melodies = $Toolkit1->getMelodiesOfUser($UserId);

$i=0;
while ($i< count($Melodies)) {
	$ToSend = $ToSend . $Melodies[$i]->toXML();
	$i = $i + 1;
}

$ToSend = $ToSend . $Follows1->toXML();


$ToSend = $ToSend . "</Root>";
echo $ToSend;

?>