<?php

$CAL_ADC_25T30_V = 444; 
$CAL_ADC_25T85_V = 527; 
$output = '';		
$hue = '';
$sisenior = '';
$id = 1;
$seniorita[] =
              array(
                    "header" => 0,
                    "db"=>  0
                    ); 
$well = 0;
$ntwk_p2ring[] =
             array(
             "id" =>0,
             "device_addr" => 0,
             "battery"=>  0,
              );	

$p2ring =
          array(
             "leaf_addr" =>0,
             "temp" => 0,
             "battery"=>  0,
             "hum" => 0,
             "rssi" => 0
             );

/*return 1 on success, */


/*returns -1 on fault */
function send_query($query)
{
		$dbhost = '';
		$dbuser = '';
		$dbpass = '';
		$dbname = '';

		$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

		$retval = mysqli_query($conn,$query);
		
		if(!$retval )
		{	
			
   			return -1; 
		}
		else
		{
			
			return $retval;

		}

		mysqli_close($conn); 
}
function update_ntwk_map($p2ring)
{
	
	$query_ntwk = "SELECT  * FROM ntwk_map";
	$sql_insert = "INSERT INTO ntwk_map ". "(device_addr, battery) ". "VALUES ". "({$p2ring['leaf_addr']}, {$p2ring['battery']})";
	$query_update = "UPDATE ntwk_map SET battery = {$p2ring['battery']} WHERE device_addr = {$p2ring['leaf_addr']} LIMIT 1;";
		
	$retval = send_query($query_ntwk); /* get mapped network devices*/

	/*table is not empty */
	if($retval)
	{	
		/*search for duplicate*/
		while($row2 = mysqli_fetch_array($retval))
		{	
			if($p2ring['leaf_addr'] ==  $row2["device_addr"])
			{
			
				/*duplicate found, update fields*/
				
				send_query($query_update);
				return 1;

			}

		}
		
		/* table not empty but no record */
		send_query($sql_insert); /*update*/
		return 1;	
	}
	else /*table is empty, add record*/
	{	
	
		send_query($sql_insert);
		return 1;

	}		
}

/* open file and read content */
$filename = "/home/pi/Monitoring/serial.log";
while(1)
{ 
	if( file_exists($filename) )
	{ 
		usleep(100000);
		$file = fopen( $filename, "r" );

		$filesize = filesize( $filename );
		$filetext = fread( $file, $filesize );
		fclose( $file );
		unlink($filename);
		foreach( explode( "@", $filetext) as $line) /* TODO: clear file after reading */
		{	

			if(strlen($line) > 33)
			{	   
		 		
				$sisenior = str_split($line, 2);
        
        			$offset = 3;
        			$hey = 0;
        			for( $hey = 0; ($hey + $offset + 3) <= (count($sisenior)-2); $hey++ ) /* parse the byte sequence*/
        			{
           				if($hey==2)
            				{
                				$leaf_addr = $sisenior[$hey];
                				$p2ring["leaf_addr"] = $leaf_addr;
            				}
            
            				$seniorita[$well] =
                            					array(
                                    					"header" => $sisenior[$hey + $offset],
                                    					"db"=>  $sisenior[$hey + $offset + 1].$sisenior[$hey + $offset + 2],  
                                    					); 
                                        
            				if($seniorita[$well]["header"] == "0x02")
            				{
                
               					$uus = hexdec($seniorita[$well]["db"]);
               					$temp = ((($uus-$CAL_ADC_25T30_V)*((85-30)/($CAL_ADC_25T85_V-$CAL_ADC_25T30_V))) + 30 );
             				 	 $p2ring["temp"] = $temp;
               
            				}
            				
            				if($seniorita[$well]["header"] == "0x01")
           					{
                
               					$uus6 = hexdec($seniorita[$well]["db"]);	
               					$battery = ((($uus6/1024) * 2.5)* 2);
               					$p2ring["battery"] = $battery;
               					$batteryout = $battery;
            				}
            
            				if($seniorita[$well]["header"] == "0x03")
            				{
              					$uus8 = hexdec($seniorita[$well]["db"]);
              					$abi1 = ($p2ring["battery"]/2);
						 echo "abi1: {$abi1}\n";
						$abi2 = ($abi1 - 0.7);
						$abi4 = (($abi2/2.5) * 1024);
						$abi5 = (($abi1/2.5) * 1024);
						echo "abi5: {$abi5}\n";
						$abi6 = ($abi5-$abi4);
						echo "abi6: {$abi6}\n";
						$abi7 = 95-65;
						$abi8 = ($abi7/$abi6);
						echo "abi8: {$abi8}\n";
						$abi9 = ($abi5 - $uus8);
						if($abi9 <= 0)
						{
						$abi9 = 0;
						}	
					 	echo "uus8: {$uus8}\n";
						echo "abi9: {$abi9}\n";
						$abi10 = ($abi9 * $abi8);
						echo "abi10: {$abi10}\n";
						$hum = (65 + $abi10); 
						echo "hum: {$hum}\n";
						$p2ring["hum"] = $hum;
            				}
            
            				if($seniorita[$well]["header"] == "0x04")
            				{
               				$uus9 = str_split($seniorita[$well]["db"], 2);
               				$uus10 = hexdec($uus9[0]);
               				$p2ring["rssi"] = $uus10;
              				
               
           				 }
                    			$well++;
                    			$offset +=2;            
		            }
 	                    
         	             //print_r("\n");       
//			}
			
    		/*send package to database*/
    		$date = date('Y-m-d h:i:sa\n');
    		$battery = $p2ring['battery'];
    		$temp = $p2ring['temp'];
    		$humiditys = $p2ring['hum'];	
    		$rssi = $p2ring['rssi'];
    		$leaf_addr = $p2ring['leaf_addr'];

			$sql = "INSERT INTO data2 ".
           			"(timestamp, temp, hum, battery, rssi, leaf_addr) ".
           			"VALUES ".
           			"('$date','$temp','$humiditys','$battery', '$rssi', '$leaf_addr')";
				
			send_query($sql);

			update_ntwk_map($p2ring);
			
			}

		}
	}
}
?>
