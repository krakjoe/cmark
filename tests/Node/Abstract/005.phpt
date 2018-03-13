--TEST--
CommonMark\Node Prepend Child TypeError
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->prependChild([]);
} catch (TypeError $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
