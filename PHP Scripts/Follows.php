<?php


class Follows
{
	var $Follower;
	var $Followed;
	var $Date;
	var $Key_Follower;
	var $Key_Followed;
	var $Key_Date;
	var $Converter;

	function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

    function __construct2($Follower,$Followed)
    {
      $this->__construct0();
      $this->Follower=$Follower;
      $this->Followed=$Followed;
      $this->select();
    }

    function __construct0()
    {
      $this->Converter=new Bridge("Follows");
      $this->setKeys();
    }

    function setKeys()
    {
    	$this->Key_Follower=$this->Converter->Attributes[0];
    	$this->Key_Followed=$this->Converter->Attributes[1];
    	$this->Key_Date=$this->Converter->Attributes[2];
    }

	function setFollower($par)
	{
		$this->Follower=$par;
	}

	function setFollowed($par)
	{
		$this->Followed=$par;
	}

	function setDate($par)
	{
		$this->Date=date("Y-m-d",strtotime($par));
	}

	function getFollower()
	{
		return $this->Follower;
	}

	function getFollowed()
	{
		return $this->Followed;
	}

	function getDate()
	{
		return $this->Date;
	}

	function insert()
	{
		$Keys[0]=$this->Key_Follower;
		$Keys[1]=$this->Key_Followed;
		$Keys[2]=$this->Key_Date;
		$Values = array($this->Follower,$this->Followed,"'$this->Date'");
		$this->Converter->insert($Keys,$Values);
	}

	function update()
	{
		$Keys = array($this->Key_Date);
		$Values = array("'$this->Date'");
		$ParaKeys = array($this->Key_Follower,$this->Key_Followed);
		$ParaValues = array($this->Follower,$this->Followed);
		$this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
	}

	function setFollows($Result)
	{
		$this->Follower=$Result[$this->Key_Follower];
		$this->Followed=$Result[$this->Key_Followed];
		$this->Date=$Result[$this->Key_Date];
	}

	function select()
	{
		$Keys = array($this->Key_Follower,$this->Key_Followed);
		$Values = array($this->Follower,$this->Followed);
		$Results=$this->Converter->select($Keys,$Values);
      	$i=0;
      	while ($i<count($Results)) 
      	{
      		$this->setFollows($Results[$i]);
      		$i=$i+1;
      	}
	}

	function delete()
	{
		$Keys = array($this->Key_Follower,$this->Key_Followed);
		$Values = array($this->Follower,$this->Followed);
		$this->Converter->delete($Keys,$Values);
	}

	function display()
	{
		echo "Follows <br/>";
		echo "Follower : " . $this->Follower . "<br/>";
		echo "Followed : " . $this->Followed . "<br/>";
		echo "Date : " . $this->Date . "<br/>";
	}


}
?>