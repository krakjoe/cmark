--TEST--
CommonMark\Node Prepend Child RuntimeException
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->prependChild(new CommonMark\Node\Document);
} catch (RuntimeException $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
