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

$User1 = new User($UserId);
$Toolkit1 = new Toolkit();

$ToSend = "<Root>";

$ToSend = $ToSend . "<Body>";

	$j = 0;
	$k = 0;
	$Melodies = $Toolkit1->getMelodiesOfUser($UserId);
	while ($j <count($Melodies)) 
	{
		$Feeds[$k] = new CreateFeed($UserId,$Melodies[$j]->getId(),"Create",$Melodies[$j]->getDate());
		$Dates[$k] = $Melodies[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}

	$j = 0;
	$Shares = $Toolkit1->getSharedMelodies($UserId);
	while ($j <count($Shares)) 
	{
		$Melody = new Melody($Shares[$j]->getMelody());
		$Original = new User($Melody->getUser_Id());
		$Feeds[$k] = new ShareFeed($UserId,$Melody->getId(),$Original->getId(),"Share",$Shares[$j]->getDate());
		$Dates[$k] = $Shares[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}

	array_multisort($Dates, $Feeds);
	$i=0;

	while ($i<count($Feeds)) {
	$ToSend = $ToSend . $Feeds[$i]->toXML();
	$i=$i+1;
}


$ToSend = $ToSend . "</Body>";
$ToSend = $ToSend . "</Root>";
echo $ToSend;
echo count($Feeds);

?>