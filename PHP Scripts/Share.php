<?php


class Share
{
	var $Sharer;
	var $Melody;
	var $Date;
	var $Key_Sharer;
	var $Key_Melody;
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

    function __construct2($Sharer,$Melody)
    {
      $this->__construct0();
      $this->Sharer=$Sharer;
      $this->Melody=$Melody;
      $this->select();
    }

    function __construct0()
    {
      $this->Converter=new Bridge("Share");
      $this->setKeys();
    }

    function setKeys()
    {
    	$this->Key_Sharer=$this->Converter->Attributes[0];
    	$this->Key_Melody=$this->Converter->Attributes[1];
    	$this->Key_Date=$this->Converter->Attributes[2];
    }

	function setSharer($par)
	{
		$this->Sharer=$par;
	}

	function setMelody($par)
	{
		$this->Melody=$par;
	}

	function setDate($par)
	{
		$this->Date=date("Y-m-d H:i:s",strtotime($par));
	}

	function getSharer()
	{
		return $this->Sharer;
	}

	function getMelody()
	{
		return $this->Melody;
	}

	function getDate()
	{
		return $this->Date;
	}

	function insert()
	{
        $Keys[0]=$this->Key_Sharer;
        $Keys[1]=$this->Key_Melody;
        $Keys[2]=$this->Key_Date;
		$Values = array($this->Sharer,$this->Melody,"'$this->Date'");
		$this->Converter->insert($Keys,$Values);
	}

	function update()
	{
		$Keys = array($this->Key_Date);
		$Values = array("'$this->Date'");
		$ParaKeys = array($this->Key_Sharer,$this->Key_Melody);
		$ParaValues = array($this->Sharer,$this->Melody);
		$this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
	}

	function setShare($Result)
	{
		$this->Sharer=$Result[$this->Key_Sharer];
		$this->Melody=$Result[$this->Key_Melody];
		$this->Date=$Result[$this->Key_Date];
	}

	function select()
	{
		$Keys = array($this->Key_Sharer,$this->Key_Melody);
		$Values = array($this->Sharer,$this->Melody);
		$Results=$this->Converter->select($Keys,$Values);
		$this->setShare($Results[0]);
      	$i=1;
      	while ($i<count($Results)) 
      	{
      		$this->setShare($Results[$i]);
      		$i=$i+1;
      	}
	}

	function delete()
	{
		$Keys = array($this->Key_Sharer,$this->Key_Melody);
		$Values = array($this->Sharer,$this->Melody);
		$this->Converter->delete($Keys,$Values);
	}

	function display()
	{
		echo "Share <br/>";
		echo "Sharer : " . $this->Sharer . "<br/>";
		echo "Melody : " . $this->Melody . "<br/>";
		echo "Date : " . $this->Date . "<br/>";
	}

	function toXML()
	{
		$echo = "<Share>";
      	$echo = $echo . "<Sharer>" . $this->Sharer . "</Sharer>";
      	$echo = $echo . "<Melody>" . $this->Melody . "</Melody>";
      	$echo = $echo . "<Date>" . $this->Date . "</Date>";
      	$echo = $echo . "</Share>";
      	return $echo ;
	}


}
?>