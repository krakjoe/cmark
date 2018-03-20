--TEST--
CommonMark\Node Previous None
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->previous) {
	echo "OK";
}
?>
--EXPECT--
OK
