--TEST--
CommonMark\Node replace invalid call
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$para->replace([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
