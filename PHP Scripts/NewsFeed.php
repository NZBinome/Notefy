<?php

include 'User.php';
include 'Melody.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'Feed.php';
include 'Share.php';
include 'Follows.php';
include 'Comment.php';
include 'Applause.php';


$UserId = $_GET['UserId'];


$Toolkit1 = new Toolkit();

$Followed =  $Toolkit1->getFollowed($UserId);


$i = 0;
$k = 0;

while ($i<count($Followed)) 
{
	$Users[$i] = new User($Followed[$i]->getFollowed());

	$j = 0;
	$Melodies = $Toolkit1->getMelodiesOfUser($Users[$i]->getId());
	while ($j <count($Melodies)) 
	{
		$Feeds[$k] = new Feed($Users[$i]->getId(),$Melodies[$j]->getId(),"Create",$Melodies[$j]->getDate());
		$Dates[$k] = $Melodies[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Shares = $Toolkit1->getSharedMelodies($Users[$i]->getId());
	while ($j <count($Shares)) 
	{
		$Melody = new Melody($Shares[$j]->getMelody());
		$Feeds[$k] = new Feed($Users[$i]->getId(),$Melody->getId(),"Share",$Shares[$j]->getDate());
		$Dates[$k] = $Shares[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Comments = $Toolkit1->getCommentsOfUser($Users[$i]->getId());
	while ($j <count($Comments)) 
	{
		$Melody = new Melody($Comments[$j]->getMelody());
		$Feeds[$k] = new Feed($Users[$i]->getId(),$Melody->getId(),"Comment",$Comments[$j]->getDate());
		$Dates[$k] = $Comments[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Applaue = $Toolkit1->getApplauseofUser($Users[$i]->getId());
	while ($j <count($Applaue)) 
	{
		$Melody = new Melody($Applaue[$j]->getMelody());
		$Feeds[$k] = new Feed($Users[$i]->getId(),$Melody->getId(),"Applause",$Applaue[$j]->getDate());
		$Dates[$k] = $Applaue[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}



	$i = $i + 1;
}

array_multisort($Dates, $Feeds);

$i=0;
$ToSend = "<Root>";

while ($i<count($Feeds)) {
	$ToSend = $ToSend . $Feeds[$i]->toXML();
	$i=$i+1;
}

$ToSend = $ToSend . "</Root>";

echo "$ToSend";

?>