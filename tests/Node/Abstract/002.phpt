--TEST--
CommonMark\Node Append Child TypeError
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->appendChild([]);
} catch (TypeError $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
