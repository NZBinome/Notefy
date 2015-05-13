<?php


class ApplauseFeed 
{
	var $Date;
	var $Type;
	var $User;
	var $Melody;
	var $ApplauseCount;
	var $ShareCount;
	var $CommentCount;


	function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

	function __construct4($UserId,$MelodyId,$type,$Time)
	{
		$this->User = new User($UserId);
		$this->Melody = new Melody ($MelodyId);
		$this->Type = $type;
		$this->Date = $Time;
		$this->getCounts();
	}

	function getCounts()
	{
		$Toolkit1 = new Toolkit();
		$this->ApplauseCount = $Toolkit1->getApplauseCount($this->Melody->getId());
		$this->ShareCount = $Toolkit1->getShareCount($this->Melody->getId());
		$this->CommentCount = $Toolkit1->getCommentCount($this->Melody->getId());
	}

	function toXML()
	{
		$ToSend = "<$this->Type>";
		$ToSend = $ToSend ."<Date> $this->Date </Date>";
		$ToSend = $ToSend . $this->User->toXML();
		$ToSend = $ToSend . $this->Melody->toXML();
		$ToSend = $ToSend ."<ApplauseCount> $this->ApplauseCount </ApplauseCount>";
		$ToSend = $ToSend ."<ShareCount> $this->ShareCount </ShareCount>";
		$ToSend = $ToSend ."<CommentCount> $this->CommentCount </CommentCount>";
		$ToSend = $ToSend . "</$this->Type>";
		return $ToSend;
	}
}

?>