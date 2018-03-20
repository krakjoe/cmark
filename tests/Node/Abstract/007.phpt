--TEST--
CommonMark\Node Next
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->next) {
	echo "OK";
}
?>
--EXPECT--
OK
