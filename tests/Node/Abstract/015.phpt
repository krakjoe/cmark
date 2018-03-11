--TEST--
CommonMark\Node Insert Before Error Structure
--FILE--
<?php
$document = new CommonMark\Node\Document;
try {
	$document->insertBefore(new CommonMark\Node\Document);
} catch(RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
