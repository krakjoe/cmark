--TEST--
CommonMark\Node Next
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->getNext()) {
	echo "OK";
}
?>
--EXPECT--
OK
