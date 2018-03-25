--TEST--
CommonMark\Node accept
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);
$para->appendChild(
	new CommonMark\Node\Text("OK"));

$doc->accept(new class implements CommonMark\Interfaces\IVisitor {
	public function enter(CommonMark\Interfaces\IVisitable $node) {
		if ($node instanceof CommonMark\Node\Text) {
			echo $node->literal;
		}
	}

	public function leave(CommonMark\Interfaces\IVisitable $node) {}
});
?>
--EXPECT--
OK
