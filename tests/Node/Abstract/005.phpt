--TEST--
CommonMark\Node Prepend Child InvalidArgumentException
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->prependChild([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
