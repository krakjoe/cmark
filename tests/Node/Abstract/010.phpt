--TEST--
CommonMark\Node Previous None
--FILE--
<?php
$document = new CommonMark\Node\Document;

if (!$document->getPrevious()) {
	echo "OK";
}
?>
--EXPECT--
OK
