--TEST--
CommonMark\Node Append Child InvalidArgumentException
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->appendChild([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
