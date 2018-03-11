--TEST--
CommonMark\Node Append Child RuntimeException
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->appendChild(new CommonMark\Node\Document);
} catch (RuntimeException $ex) {
	echo "OK";	
}
?>
--EXPECT--
OK
