<?php
/* class to add packet to database 
    TODO: read packet length from it and do dynamic array
*/

/* open file and read content */
$filename = "RX.log";
$file = fopen( $filename, "r" );
 
if( $file == false ) {
echo ( "Error in opening file" );
exit();
}        
 
$filesize = filesize( $filename );
$filetext = fread( $file, $filesize );
fclose( $file );

/*[0-9]+\D[0-9]+\D[0-9]+\D[0-9]+\D[0-9]+\D[0-9]+\D[0-9]+\D{2}[0-9 | A-W]+*/
/* (\d+\D)+(\D+\d+)+ */
/* ( [a-f0-9]+)+ */
/* /\[.+\] [a-f0-9].+/ *//*working with 1 space*/

$CAL_ADC_25T30_V = 444; 
$CAL_ADC_25T85_V = 527; 
$dbhost = 'localhost:3306';
$dbuser = 'root';
$dbpass = 'Marvintherobot';
$dbname = 'lillepott';
$battery = 0;
$temp = 0;
$hum = 0; 
$rssi = 0;
$output = '';
$hue = '';
$sisenior = '';
$id = 1;
$seniorita[] =
                    array(
                    "header" => 0,
                    "db"=>  0
                    ); 
                    
                                   
$hey = 0;
$karlito = '';
$offset = 3;
$seniorita_size = 0;
$leaf_addr = 0;
$well = 0;
$p2ring[] =
                    array(
                    "leaf_addr" =>0,
                    "temp" => 0,
                    "battery"=>  0,
                    "hum" => 0,
                    "rssi" => 0
                    );
$hesse = 0;

foreach( explode( "\n", $filetext) as $line) /*TODO: clear file after reading */
{   
    
    if( preg_match( '/\[.+\]  \S+/', $line, $matches)) 
    {   
        //echo print_r($matches[0]);
        //echo "\n";
        $hue = explode( " ", $matches[0]);  
        //print_r($hue[1]);
        //print_r("\n");
        //print_r($hue[2]);
        //print_r("\n");
        //print_r("\n");
       
        $help = $hue[3];
        $hues = explode( "[", $help);
        
        print_r($hues[0]);
        print_r("\n");
        
        $sisenior = str_split($hues[0], 2);
        echo print_r($sisenior);
        $offset = 3;
        
        for( $hey = 0; ($hey + $offset + 3) <= count($sisenior); $hey++ ) /* parse the byte sequence*/
        {
           if($hey==2)
            {
                $leaf_addr = $sisenior[$hey];
                $p2ring[$hesse]["leaf_addr"] = $leaf_addr;
            }
            
            $seniorita[$well] =
                            array(
                                    "header" => $sisenior[$hey + $offset],
                                    "db"=>  $sisenior[$hey + $offset + 1].$sisenior[$hey + $offset + 2],  
                                    ); 
                                        
           // echo "seniorita $well\n";                                    
            //echo print_r($seniorita[$well]);

            if($seniorita[$well]["header"] == "0x02")
            {
                
               $uus = hexdec($seniorita[$well]["db"]);
               $temp = ((($uus-$CAL_ADC_25T30_V)*((85-30)/($CAL_ADC_25T85_V-$CAL_ADC_25T30_V))) + 30 );
               $p2ring[$hesse]["temp"] = $temp;
               
            }
            
            if($seniorita[$well]["header"] == "0x01")
            {
                
               $uus6 = hexdec($seniorita[$well]["db"]);
               
               $battery = ((($uus6/1024) * 2.5)* 2);
               $p2ring[$hesse]["battery"] = $battery;
               
            }
            
            if($seniorita[$well]["header"] == "0x03")
            {
              $uus8 = hexdec($seniorita[$well]["db"]);
               
              $hum = ((($uus8 / 1024) * 2.5));
              $p2ring[$hesse]["hum"] = $hum;
            }
            
            if($seniorita[$well]["header"] == "0x04")
            {
               $uus9 = str_split($seniorita[$well]["db"], 2);
               $uus10 = hexdec($uus9[0]);
               $p2ring[$hesse]["rssi"] = $uus10;
              //echo print_r($seniorita[$well]);
               
            }
                    $well++;
                    $offset +=2;            
                }
                
                    //echo "leaf addr: $leaf_addr\n";    
                    //print_r("\n");       
            }
    $hesse++;
    echo"$hesse\n";
}

//echo ( "File size :$output" );
//echo ( "\nFile size : $filesize bytes \n" );

$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
 

//echo "$date";
for( $hoy = 0; $hoy < count($p2ring); $hoy++ ){
    //echo "\np2ring $hoy\n";
    //$id++;
    $date = date('Y-m-d h:i:sa\n');
    $battery = $p2ring[$hoy]['battery'];
    $temp = $p2ring[$hoy]['temp'];
    $humiditys = $p2ring[$hoy]['hum']; 
    $rssi = $p2ring[$hoy]['rssi'];
    $leaf_addr = $p2ring[$hoy]['leaf_addr'];
   // echo print_r($p2ring[$hoy]);  
    $sql = "INSERT INTO data2 ".
           "(timestamp, temp, hum, battery, rssi, leaf_addr) ".
           "VALUES ".
           "('$date','$temp','$humiditys','$battery', '$rssi', '$leaf_addr')";
         
   $retval = mysqli_query($conn,$sql);

}

//print_r($p2ring);

if(! $retval )
{
   die('Could not enter data: ' . mysqli_error($conn));
}

echo "Entered data successfully\n";

mysqli_close($conn); 

?>