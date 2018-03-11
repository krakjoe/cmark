--TEST--
CommonMark\Node Insert After Error Structure
--FILE--
<?php
$document = new CommonMark\Node\Document;
try {
	$document->insertAfter(new CommonMark\Node\Document);
} catch(RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
