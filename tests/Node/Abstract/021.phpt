--TEST--
CommonMark\Node replace invalid
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$para->replace(new CommonMark\Node\Document);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
