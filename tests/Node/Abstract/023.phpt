--TEST--
CommonMark\Node insertAfter used
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$para->insertAfter($para);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
