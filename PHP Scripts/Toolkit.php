<?php

class Toolkit
{
	var $Bridge;
	
	function __construct()
	{
		$this->Bridge=new Bridge();
	}

	function getMelodiesOfUser($UserId)
	{
		$this->Bridge->setTable("Melodies");
		$Keys = array($this->Bridge->Attributes[4]);
		$Values = array($UserId);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
        while ($i<count($Results)) 
        {
        	$Melodies[$i] = new Melody();
        	$Melodies[$i]->setMelody($Results[$i]);
           	$i=$i+1;
        }
        return $Melodies;
	}

	function getFollowers($Followed)
	{
		$this->Bridge->setTable("Follows");
		$Keys = array($this->Bridge->Attributes[1]);
		$Values = array($Followed);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) 
        {
        	$Follows[$i] = new Follows();
        	$Follows[$i]->setFollows($Results[$i]);
           	$i=$i+1;
        }
        return $Follows;
	}

	function getFollowed($Follower)
	{
		$this->Bridge->setTable("Follows");
		$Keys = array($this->Bridge->Attributes[0]);
		$Values = array($Follower);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) 
        {
        	$Follows[$i] = new Follows();
        	$Follows[$i]->setFollows($Results[$i]);
           	$i=$i+1;
        }
        return $Follows;
	}

	function getApplause($Melody)
	{
		$this->Bridge->setTable("Applause");
		$Keys = array($this->Bridge->Attributes[1]);
		$Values = array($Melody);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Applause[$i]= new Applause();
			$Applause[$i]->setApplause($Results[$i]);
			$i=$i+1;
		}
		return $Applause;
	}

	function getApplauseofUser($UserId)
	{
		$this->Bridge->setTable("Applause");
		$Keys = array($this->Bridge->Attributes[0]);
		$Values = array($UserId);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Applause[$i]= new Applause();
			$Applause[$i]->setApplause($Results[$i]);
			$i=$i+1;
		}
		return $Applause;
	}

	function getComments($Melody)
	{
		$this->Bridge->setTable("Comment");
		$Keys = array($this->Bridge->Attributes[2]);
		$Values = array($Melody);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Comment[$i]= new Comment();
			$Comment[$i]->setComment($Results[$i]);
			$i=$i+1;
		}
		return $Comment;
	}

	function getCommentsOfUser($UserId)
	{
		$this->Bridge->setTable("Comment");
		$Keys = array($this->Bridge->Attributes[1]);
		$Values = array($UserId);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Comment[$i]= new Comment();
			$Comment[$i]->setComment($Results[$i]);
			$i=$i+1;
		}
		return $Comment;
	}


	function getSharedMelodies($User)
	{
		$this->Bridge->setTable("Share");
		$Keys = array($this->Bridge->Attributes[0]);
		$Values = array($User);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Share[$i]= new Share();
			$Share[$i]->setShare($Results[$i]);
			$i=$i+1;
		}
		return $Share;
	}

	function getSharers($Melody)
	{
		$this->Bridge->setTable("Share");
		$Keys = array($this->Bridge->Attributes[1]);
		$Values = array($Melody);
		$Results = $this->Bridge->select($Keys,$Values);
		$i=0;
		while ($i<count($Results)) {	
			$Share[$i]= new Share();
			$Share[$i]->setShare($Results[$i]);
			$i=$i+1;
		}
		return $Share;
	}

	
}


?>